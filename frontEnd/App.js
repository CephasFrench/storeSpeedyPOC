import React, { useState } from 'react';
import { StyleSheet, Text, View, TextInput, Button, FlatList, TouchableOpacity, Alert } from 'react-native';
import { StatusBar } from 'expo-status-bar';
import { AntDesign } from '@expo/vector-icons';

export default function App() {
    const [location, setLocation] = useState('Valley Mills'); // State to store the location
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

    // Function to "save" the location, which currently just triggers an alert
    const handleSaveLocation = () => {
        Alert.alert("Success", "Location saved successfully!");
    };

    return (
        <View style={styles.container}>
            <Text style={styles.header}>StoreSpeedy</Text>
            <InputWithButton
                label="Enter location..."
                value={location}
                onChangeText={setLocation}
                buttonLabel="Save"
                onPressButton={handleSaveLocation}
            />
            <InputWithButton
                label="Enter grocery item..."
                value={item}
                onChangeText={setItem}
                buttonLabel="Add"
                onPressButton={handleAddItem}
            />
            <GroceryList items={groceryList} onRemoveItem={handleRemoveItem} />
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
                color="#5e60ce"
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
        justifyContent: 'flex-start',
        paddingTop: 60,
        paddingHorizontal: 20,
        width: '100%',
        height: '100%',
        backgroundColor: '#fff0f0', // Set to a light red/white blend background
    },
    header: {
        fontSize: 26,
        marginBottom: 20,
        color: '#1d3557',
        fontWeight: 'bold',
    },
    inputContainer: {
        flexDirection: 'row',
        width: '100%',
        alignItems: 'center',
        marginBottom: 10,
    },
    input: {
        height: 40,
        flex: 1,
        borderWidth: 1,
        padding: 10,
        borderColor: '#ced4da',
        borderRadius: 5,
        backgroundColor: '#ffffff',
    },
    list: {
        width: '100%',
    },
    listItem: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        padding: 10,
        backgroundColor: '#ffffff',
        borderWidth: 1,
        borderColor: '#adb5bd',
        borderRadius: 5,
        marginBottom: 10,
    },
    itemText: {
        fontSize: 16,
        color: '#343a40',
    },
});
