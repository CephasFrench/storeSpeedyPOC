import React, { useState } from 'react';
import { StyleSheet, Text, View, TextInput, Button, FlatList, TouchableOpacity, Alert } from 'react-native';
import { Picker } from '@react-native-picker/picker';
import { StatusBar } from 'expo-status-bar';
import { AntDesign } from '@expo/vector-icons';

const validLocations = ["Default", "Valley Mills"]; // Structure to hold the list of valid choices for locations

export default function App() {
    const [location, setLocation] = useState('Default'); // State to store the location
    const [item, setItem] = useState(''); // State to store the current input item
    const [groceryList, setGroceryList] = useState([]); // State to store the list of grocery items

    // Function to add an item to the grocery list
    const handleAddItem = () => {
        if (!item.trim()) {
            Alert.alert("Validation", "Please enter an item name.");
            return;
        }
        setGroceryList([...groceryList, item]);
        setItem('');
    };

    // Function to remove an item from the grocery list
    const handleRemoveItem = (index) => {
        setGroceryList(groceryList.filter((_, i) => i !== index));
    };

    // Function to generate route and communicate with the C++ backend
    const handleGenerateRoute = () => {
        // Data structure to send to the backend
        const requestData = {
            location,
            groceryList
        };

        // Send the data to the backend server
        fetch('http://localhost:8080/generate-route', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(requestData),
        })
        .then(response => response.json())  // Expect JSON response
        .then(data => {
            console.log("Response from backend:", data);
            Alert.alert("Route", `Response from backend: ${data.message}`);
        })
        .catch((error) => {
            console.error('Error:', error);
            Alert.alert("Error", "Failed to communicate with the backend server.");
        });
    };

    return (
        <View style={styles.container}>
            <Text style={styles.header}>StoreSpeedy</Text>
            <Text style={styles.subHeader}>Navigate HEB Stores Efficiently</Text>
            <Text style={styles.label}>Location:</Text>
            <View style={styles.pickerContainer}>
                <Picker
                    selectedValue={location}
                    style={styles.picker}
                    onValueChange={(itemValue) => setLocation(itemValue)}
                    mode="dropdown" // Ensures the picker expands only when clicked
                >
                    {validLocations.map((loc) => (
                        <Picker.Item key={loc} label={loc} value={loc} />
                    ))}
                </Picker>
            </View>
            <InputWithButton
                label="Enter grocery item..."
                value={item}
                onChangeText={setItem}
                buttonLabel="Add"
                onPressButton={handleAddItem}
            />
            <GroceryList items={groceryList} onRemoveItem={handleRemoveItem} />
            <TouchableOpacity style={styles.button} onPress={handleGenerateRoute}>
                <Text style={styles.buttonText}>Generate Route</Text>
            </TouchableOpacity>
            <StatusBar style="auto" />
        </View>
    );
}

// Component for input with a button
function InputWithButton({ label, value, onChangeText, buttonLabel, onPressButton }) {
    return (
        <View style={styles.inputContainer}>
            <TextInput
                style={styles.input}
                onChangeText={onChangeText}
                value={value}
                placeholder={label}
            />
            <Button
                title={buttonLabel}
                onPress={onPressButton}
                color="#ff0000" // Red color for buttons
            />
        </View>
    );
}

// Component for displaying and managing the grocery list
function GroceryList({ items, onRemoveItem }) {
    return (
        <FlatList
            style={styles.list}
            data={items}
            renderItem={({ item, index }) => (
                <View style={styles.listItem}>
                    <Text style={styles.itemText}>{item}</Text>
                    <TouchableOpacity onPress={() => onRemoveItem(index)}>
                        <AntDesign name="delete" size={24} color="red" />
                    </TouchableOpacity>
                </View>
            )}
            keyExtractor={(_, index) => index.toString()}
        />
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        paddingTop: 60,
        paddingHorizontal: 20,
        backgroundColor: '#ffffff', // White background
    },
    header: {
        fontSize: 26,
        marginBottom: 10,
        color: '#1d3557',
        fontWeight: 'bold',
    },
    subHeader: {
        fontSize: 18,
        marginBottom: 20,
        color: '#1d3557',
    },
    label: {
        fontSize: 18,
        marginBottom: 10,
        color: '#1d3557',
    },
    pickerContainer: {
        width: '100%',
        marginBottom: 20,
        borderColor: '#000000', // Black border
        borderWidth: 1,
        borderRadius: 5,
        overflow: 'hidden',
    },
    picker: {
        width: '100%',
    },
    inputContainer: {
        flexDirection: 'row',
        width: '100%',
        alignItems: 'center',
        marginBottom: 10,
        borderColor: '#000000', // Black border
        borderWidth: 1,
        borderRadius: 5,
    },
    input: {
        height: 40,
        flex: 1,
        borderWidth: 0, // Remove border from input field
        padding: 10,
        backgroundColor: '#ffffff',
    },
    list: {
        width: '100%',
        marginBottom: 20,
    },
    listItem: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        padding: 10,
        backgroundColor: '#ffffff',
        borderWidth: 1,
        borderColor: '#000000', // Black border
        borderRadius: 5,
        marginBottom: 10,
    },
    itemText: {
        fontSize: 16,
        color: '#343a40',
    },
    button: {
        backgroundColor: '#ff0000', // Red background
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
