import React, { useState, useEffect } from 'react';
import { StyleSheet, Text, View, TouchableOpacity, Alert, SafeAreaView, FlatList, TextInput } from 'react-native';
import { Picker } from '@react-native-picker/picker';
import { StatusBar } from 'expo-status-bar';
import * as SecureStore from 'expo-secure-store';
import { BOOLEAN_VALUES, USR_INPT_CHAR_LMT } from './config'; // Corrected relative paths

const validLocations = ["Default", "ValleyMills"];
const SERVER_URL     = "http://localhost:8080";     // Replace localhost with true server URL
const userId         = 'default';                   // default user ID

export default function App() {
    // State management hooks
    const [location, setLocation] = useState('Default');
    const [item, setItem] = useState('');
    const [groceryList, setGroceryList] = useState([]);
    const [aisles, setAisles] = useState([]);
    const [isDeveloper, setIsDeveloper] = useState(BOOLEAN_VALUES.DEVELOPER_MODE);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState('');

    // Effect to update location on the server
    useEffect(() => {
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

    // Effect to fetch developer mode status from secure storage
    useEffect(() => {
        const fetchDeveloperMode = async () => {
            const storedIsDeveloper = await SecureStore.getItemAsync('isDeveloper');
            setIsDeveloper(storedIsDeveloper === 'true');
        };

        fetchDeveloperMode();
    }, []);

    // Fetch grocery list from the server
    const fetchGroceryList = async () => {
        try {
            const response = await fetch(`${SERVER_URL}/grocery_list/${userId}/${location}`);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log('Fetched grocery list:', data);

            if (Array.isArray(data.items)) {
                setGroceryList(data.items);
            } else if (Array.isArray(data)) {
                setGroceryList(data);
            } else {
                throw new Error('Invalid items data. Expected an array of items.');
            }
        } catch (error) {
            console.error('Error fetching grocery list:', error);
            setError(`Failed to load items: ${error.message}`);
        } finally {
            setLoading(false);
        }
    };

    // Fetch grocery list on location change
    useEffect(() => {
        fetchGroceryList();
    }, [location]);

    // Handle adding an item to the grocery list
    const handleAddItem = async () => {
        if (!item.trim()) {
            Alert.alert("Validation", "Please enter an item name.");
            return;
        }

        if (groceryList.includes(item.trim())) {
            setItem(''); // Clear the text entry box
            Alert.alert("Duplicate Item", "This item is already in your grocery list.");
            return;
        }

        try {
            const response = await fetch(`${SERVER_URL}/check_item`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ item }),
            });

            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }

            const data = await response.text(); // Expect plain text "YES" or "NO"
            console.log('Response from backend:', data);

            if (data === "YES") {
                fetchGroceryList(); // Refresh the grocery list from the server
                Alert.alert("Item Available", `${item} is available at HEB and added to your list.`);
            } else if (data === "NO") {
                Alert.alert("Item Unavailable", `${item} is not available at HEB.`);
            } else {
                Alert.alert("Duplicate Item", "This item is already in your grocery list.");
            }
        } catch (error) {
            console.error('Error checking item availability:', error);
            Alert.alert("Error", `Failed to check item availability: ${error.message}`);
        } finally {
            setItem(''); // Clear the text entry box
        }
    };

    // Handle removing an item from the grocery list
    const handleRemoveItem = async (index) => {
        const itemToRemove = groceryList[index];
        const updatedGroceryList = groceryList.filter((_, i) => i !== index);

        try {
            const response = await fetch(`${SERVER_URL}/update_grocery_list/${userId}/${location}`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ items: updatedGroceryList }),
            });

            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }

            setGroceryList(updatedGroceryList);
            Alert.alert("Success", `${itemToRemove} has been removed from your grocery list.`);
        } catch (error) {
            console.error('Error removing item:', error);
            Alert.alert("Error", `Failed to remove item: ${error.message}`);
        }
    };

    // Handle generating a shopping route
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
                Alert.alert("Error", `Failed to fetch data from backend: ${error.message}`);
            });
    };

    // Combine grocery list and aisles data
    const combinedData = [
        { type: 'header' },
        ...groceryList.map((item, index) => ({ type: 'grocery', item, index })),
        BOOLEAN_VALUES.SHOW_GENERATE_ROUTE_BUTTON && { type: 'generateRoute' },
        BOOLEAN_VALUES.SHOW_AISLES && aisles.length > 0 && { type: 'aislesHeader' },
        ...aisles.map((item, index) => ({ type: 'aisle', item, index }))
    ].filter(Boolean);

    // Render header component
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
                        onChangeText={(text) => {
                            if (text.length <= USR_INPT_CHAR_LMT) {
                                setItem(text);
                            }
                        }}
                        onSubmitEditing={handleAddItem}
                        blurOnSubmit={false} // This allows the user to continue typing without losing focus
                    />
                    <TouchableOpacity style={styles.addButton} onPress={handleAddItem}>
                        <Text style={styles.addButtonText}>Add</Text>
                    </TouchableOpacity>
                </View>
            )}
            <Text style={styles.listHeader}>Grocery List</Text>
        </>
    );

    // Render the loading screen
    if (loading) {
        return (
            <SafeAreaView style={styles.safeArea}>
                <Text>Loading...</Text>
            </SafeAreaView>
        );
    }

    // Render the error screen
    if (error) {
        return (
            <SafeAreaView style={styles.safeArea}>
                <Text style={styles.errorText}>{error}</Text>
            </SafeAreaView>
        );
    }

    // Main render
    return (
        <SafeAreaView style={styles.safeArea}>
            <FlatList
                data={combinedData}
                renderItem={({ item }) => {
                    if (item.type === 'header') {
                        return renderHeader();
                    } else if (item.type === 'grocery') {
                        return (
                            <View style={styles.itemContainer}>
                                <Text style={styles.itemText}>{item.item}</Text>
                                <TouchableOpacity style={styles.removeButton} onPress={() => handleRemoveItem(item.index)}>
                                    <Text style={styles.removeButtonText}>Remove</Text>
                                </TouchableOpacity>
                            </View>
                        );
                    } else if (item.type === 'generateRoute') {
                        return (
                            <TouchableOpacity style={styles.button} onPress={handleGenerateRoute}>
                                <Text style={styles.buttonText}>Generate Route</Text>
                            </TouchableOpacity>
                        );
                    } else if (item.type === 'aislesHeader') {
                        return <Text style={styles.listHeader}>Aisles</Text>;
                    } else if (item.type === 'aisle') {
                        return (
                            <View style={styles.aisleContainer}>
                                <Text style={styles.aisleText}>{item.item}</Text>
                            </View>
                        );
                    }
                    return null;
                }}
                keyExtractor={(item, index) => `${item.type}-${index}`}
            />
            <StatusBar style="auto" />
        </SafeAreaView>
    );
}

// Stylesheet for the app
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
    itemContainer: {
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between',
        padding: 10,
        borderBottomWidth: 1,
        borderBottomColor: '#ccc',
    },
    itemText: {
        fontSize: 16,
        color: '#1d3557',
    },
    removeButton: {
        backgroundColor: '#ff0000',
        paddingVertical: 5,
        paddingHorizontal: 10,
        borderRadius: 5,
    },
    removeButtonText: {
        color: '#fff',
        fontSize: 14,
    },
    aisleContainer: {
        padding: 10,
        borderBottomWidth: 1,
        borderBottomColor: '#ccc',
    },
    aisleText: {
        fontSize: 16,
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
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});
