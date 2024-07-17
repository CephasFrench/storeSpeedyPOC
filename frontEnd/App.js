import React, { useState, useEffect } from 'react';
import { StyleSheet, Text, View, TouchableOpacity, Alert, SafeAreaView, FlatList, TextInput } from 'react-native';
import { Picker } from '@react-native-picker/picker';
import { StatusBar } from 'expo-status-bar';
import { AntDesign } from '@expo/vector-icons'; // Import AntDesign
import * as SecureStore from 'expo-secure-store';
import { BOOLEAN_VALUES } from '/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd/config';

const validLocations = ["Default", "Valley Mills"];

export default function App() {
    const [location, setLocation] = useState('Default');
    const [item, setItem] = useState('');
    const [groceryList, setGroceryList] = useState([]);
    const [aisles, setAisles] = useState([]);
    const [isDeveloper, setIsDeveloper] = useState(BOOLEAN_VALUES.DEVELOPER_MODE);

    useEffect(() => {
        // Update the server with the new location whenever it changes
        const updateLocation = async () => {
            try {
                await fetch('http://localhost:8080/update_location', {
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

    // Function to handle adding an item to the grocery list
    const handleAddItem = () => {
        if (!item.trim()) {
            Alert.alert("Validation", "Please enter an item name.");
            return;
        }
        const updatedGroceryList = [...groceryList, item];
        setGroceryList(updatedGroceryList);
        setItem('');
        handleUpdateAisleData(updatedGroceryList);
    };

    // Function to handle removing an item from the grocery list
    const handleRemoveItem = (index) => {
        const updatedGroceryList = groceryList.filter((_, i) => i !== index);
        setGroceryList(updatedGroceryList);
        handleUpdateAisleData(updatedGroceryList);
    };

    // Function to fetch route from the backend and update the aisles state
    const handleGenerateRoute = () => {
        fetch('http://localhost:8080/compute_path')
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

    // Function to update aisle data from the frontend to the backend
    const handleUpdateAisleData = (updatedGroceryList) => {
        const updatedData = { items: updatedGroceryList }; // Update this structure as needed
        fetch('http://localhost:8080/update_aisle_data', {
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
                Alert.alert("Success", "Aisle data updated successfully.");
            })
            .catch((error) => {
                console.error('Error updating data:', error);
                Alert.alert("Error", "Failed to update aisle data.");
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
                        autoCorrect={false}
                    />
                    <TouchableOpacity style={styles.addButton} onPress={handleAddItem}>
                        <Text style={styles.addButtonText}>Add</Text>
                    </TouchableOpacity>
                </View>
            )}
            <Text style={styles.listHeader}>Grocery List</Text>
        </>
    );

    // Function to render grocery list items
    const renderGroceryItem = ({ item, index }) => (
        <View style={styles.listItem}>
            <Text style={styles.itemText}>{item}</Text>
            <TouchableOpacity onPress={() => handleRemoveItem(index)}>
                <AntDesign name="delete" size={24} color="red" />
            </TouchableOpacity>
        </View>
    );

    // Function to render aisle items
    const renderAisleItem = ({ item }) => (
        <View style={styles.listItem}>
            <Text style={styles.aisleName}>{item.aisleName}</Text>
            {item.items.map((itemName, index) => (
                <Text key={index} style={styles.itemText}>{itemName}</Text>
            ))}
        </View>
    );

    return (
        <SafeAreaView style={styles.safeArea}>
            <FlatList
                ListHeaderComponent={renderHeader}
                data={groceryList}
                renderItem={renderGroceryItem}
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
                    renderItem={renderAisleItem}
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
    },
    input: {
        flex: 1,
        borderColor: '#000',
        borderWidth: 1,
        borderRadius: 5,
        padding: 10,
        marginRight: 10,
    },
    addButton: {
        backgroundColor: '#ff0000',
        padding: 10,
        borderRadius: 5,
    },
    addButtonText: {
        color: '#ffffff',
        fontSize: 16,
    },
    listHeader: {
        fontSize: 18,
        fontWeight: 'bold',
        color: '#1d3557',
        marginVertical: 10,
        textAlign: 'center',
    },
    listItem: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        padding: 10,
        backgroundColor: '#ffffff',
        borderWidth: 1,
        borderColor: '#000000',
        borderRadius: 5,
        marginBottom: 10,
        width: '100%',
    },
    itemText: {
        fontSize: 16,
        color: '#343a40',
    },
    aisleName: {
        fontSize: 18,
        fontWeight: 'bold',
        color: '#1d3557',
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
});
