import React, { useState, useEffect } from 'react';
import { StyleSheet, Text, View, TouchableOpacity, Alert, SafeAreaView, FlatList, TextInput } from 'react-native';
import { Picker } from '@react-native-picker/picker';
import { StatusBar } from 'expo-status-bar';
import * as SecureStore from 'expo-secure-store';
import { BOOLEAN_VALUES } from '/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd/config';
import InputWithButton from './components/InputWithButton';
import GroceryList from './components/GroceryList';
import AisleList from './components/AisleList';

const validLocations = ["Default", "Valley Mills"];
const userId = 'default'; // default user ID
const SERVER_URL = "http://localhost:8080"; // Replace localhost when applicable

export default function App() {
    const [location, setLocation] = useState('Default');
    const [item, setItem] = useState('');
    const [groceryList, setGroceryList] = useState([]);
    const [aisles, setAisles] = useState([]);
    const [isDeveloper, setIsDeveloper] = useState(BOOLEAN_VALUES.DEVELOPER_MODE);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState('');

    useEffect(() => {
        // Update the server with the new location whenever it changes
        const updateLocation = async () => {
            try {
                await fetch(`${SERVER_URL}/update_location`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify({ location }),
                });
            } catch (error) {
                console.error('Error updating location:', error);
                Alert.alert("Error", "Failed to update location.");
            }
        };

        updateLocation();
    }, [location]);

    useEffect(() => {
        // Fetch developer mode from secure storage
        const fetchDeveloperMode = async () => {
            const storedIsDeveloper = await SecureStore.getItemAsync('isDeveloper');
            setIsDeveloper(storedIsDeveloper === 'true');
        };

        fetchDeveloperMode();
    }, []);

    useEffect(() => {
        // Fetch the grocery list when the app loads
        const fetchGroceryList = async () => {
            try {
                const response = await fetch(`${SERVER_URL}/grocery_list/${userId}/${location}`);
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                const data = await response.json();
                console.log('Fetched grocery list:', data);
                
                // Ensure the data is in the correct format
                if (Array.isArray(data.items)) {
                    setGroceryList(data.items);
                } else {
                    throw new Error('Invalid items data. Expected an array of items.');
                }
            } catch (error) {
                console.error('Error fetching grocery list:', error);
                setError('Failed to load items. Please try again later.');
            } finally {
                setLoading(false);
            }
        };

        fetchGroceryList();
    }, [location]);

    // Function to handle adding an item to the grocery list
    const handleAddItem = () => {
        if (!item.trim()) {
            Alert.alert("Validation", "Please enter an item name.");
            return;
        }
        const updatedGroceryList = [...groceryList, item];
        setGroceryList(updatedGroceryList);
        setItem('');
        handleUpdateGroceryList(updatedGroceryList);
    };

    // Function to handle removing an item from the grocery list
    const handleRemoveItem = (index) => {
        const updatedGroceryList = groceryList.filter((_, i) => i !== index);
        setGroceryList(updatedGroceryList);
        handleUpdateGroceryList(updatedGroceryList);
    };

    // Function to update grocery list in the backend
    const handleUpdateGroceryList = (updatedGroceryList) => {
        const updatedData = { items: updatedGroceryList }; // Update this structure as needed
        fetch(`${SERVER_URL}/update_grocery_list/${userId}/${location}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(updatedData),
        })
            .then((response) => {
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                handleGenerateRoute(); // Update aisles after updating aisle data
                Alert.alert("Success", "Grocery list updated successfully.");
            })
            .catch((error) => {
                console.error('Error updating data:', error);
                Alert.alert("Error", "Failed to update grocery list.");
            });
    };

    // Function to fetch route from the backend and update the aisles state
    const handleGenerateRoute = () => {
        fetch(`${SERVER_URL}/compute_path`)
            .then((response) => {
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                return response.json();
            })
            .then((data) => {
                setAisles(data);
            })
            .catch((error) => {
                console.error('Error fetching data:', error);
                Alert.alert("Error", "Failed to fetch data from backend.");
            });
    };

    // Function to render the header of the FlatList
    const renderHeader = () => (
        <>
            <Text style={styles.header}>StoreSpeedy</Text>
            <Text style={styles.subHeader}>Navigate HEB Stores Efficiently</Text>
            <Text style={styles.label}>Location:</Text>
            <View style={styles.pickerContainer}>
                <Picker
                    selectedValue={location}
                    style={styles.picker}
                    onValueChange={(itemValue) => setLocation(itemValue)}
                    mode="dropdown"
                >
                    {validLocations.map((loc) => (
                        <Picker.Item key={loc} label={loc} value={loc} />
                    ))}
                </Picker>
            </View>
            {BOOLEAN_VALUES.SHOW_ITEM_INPUT && (
                <View style={styles.inputContainer}>
                    <TextInput
                        style={styles.input}
                        placeholder="Enter grocery item..."
                        value={item}
                        onChangeText={setItem}
                        onSubmitEditing={handleAddItem}
                    />
                    <TouchableOpacity style={styles.addButton} onPress={handleAddItem}>
                        <Text style={styles.addButtonText}>Add</Text>
                    </TouchableOpacity>
                </View>
            )}
            <Text style={styles.listHeader}>Grocery List</Text>
        </>
    );

    if (loading) {
        return (
            <SafeAreaView style={styles.safeArea}>
                <Text>Loading...</Text>
            </SafeAreaView>
        );
    }

    if (error) {
        return (
            <SafeAreaView style={styles.safeArea}>
                <Text style={styles.errorText}>{error}</Text>
            </SafeAreaView>
        );
    }

    return (
        <SafeAreaView style={styles.safeArea}>
            <FlatList
                ListHeaderComponent={renderHeader}
                data={groceryList}
                renderItem={({ item, index }) => (
                    <GroceryList item={item} index={index} onRemoveItem={handleRemoveItem} />
                )}
                keyExtractor={(item, index) => index.toString()}
                ListFooterComponent={
                    BOOLEAN_VALUES.SHOW_GENERATE_ROUTE_BUTTON && (
                        <TouchableOpacity style={styles.button} onPress={handleGenerateRoute}>
                            <Text style={styles.buttonText}>Generate Route</Text>
                        </TouchableOpacity>
                    )
                }
            />
            {BOOLEAN_VALUES.SHOW_AISLES && (
                <FlatList
                    data={aisles}
                    renderItem={({ item }) => (
                        <AisleList item={item} />
                    )}
                    keyExtractor={(item, index) => index.toString()}
                    ListHeaderComponent={<Text style={styles.listHeader}>Aisles</Text>}
                />
            )}
            <StatusBar style="auto" />
        </SafeAreaView>
    );
}

const styles = StyleSheet.create({
    safeArea: {
        flex: 1,
        backgroundColor: '#ffffff',
    },
    header: {
        fontSize: 26,
        marginBottom: 10,
        color: '#1d3557',
        fontWeight: 'bold',
        textAlign: 'center',
    },
    subHeader: {
        fontSize: 18,
        marginBottom: 20,
        color: '#1d3557',
        textAlign: 'center',
    },
    label: {
        fontSize: 18,
        marginBottom: 10,
        color: '#1d3557',
        textAlign: 'center',
    },
    pickerContainer: {
        width: '100%',
        marginBottom: 20,
        borderColor: '#000000',
        borderWidth: 1,
        borderRadius: 5,
        overflow: 'hidden',
    },
    picker: {
        width: '100%',
    },
    inputContainer: {
        flexDirection: 'row',
        alignItems: 'center',
        marginBottom: 20,
        marginHorizontal: 20,
    },
    input: {
        flex: 1,
        borderColor: '#1d3557',
        borderWidth: 1,
        borderRadius: 5,
        padding: 10,
    },
    addButton: {
        marginLeft: 10,
        backgroundColor: '#1d3557',
        paddingVertical: 10,
        paddingHorizontal: 15,
        borderRadius: 5,
    },
    addButtonText: {
        color: '#fff',
        fontSize: 16,
    },
    listHeader: {
        fontSize: 18,
        fontWeight: 'bold',
        color: '#1d3557',
        marginVertical: 10,
        textAlign: 'center',
    },
    button: {
        backgroundColor: '#ff0000',
        padding: 15,
        borderRadius: 5,
        marginBottom: 20,
        alignItems: 'center',
    },
    buttonText: {
        color: '#ffffff',
        fontSize: 16,
    },
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});
