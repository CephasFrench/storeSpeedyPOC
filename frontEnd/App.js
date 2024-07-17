import React, { useState } from 'react';
import { StyleSheet, Text, View, TouchableOpacity, Alert, SafeAreaView, FlatList } from 'react-native';
import { Picker } from '@react-native-picker/picker';
import { StatusBar } from 'expo-status-bar';
import { AntDesign } from '@expo/vector-icons'; // Import AntDesign
import InputWithButton from './components/InputWithButton';

const validLocations = ["Default", "Valley Mills"];

export default function App() {
    const [location, setLocation] = useState('Default');
    const [item, setItem] = useState('');
    const [groceryList, setGroceryList] = useState([]);
    const [aisles, setAisles] = useState([]);

    const handleAddItem = () => {
        if (!item.trim()) {
            Alert.alert("Validation", "Please enter an item name.");
            return;
        }
        setGroceryList([...groceryList, item]);
        setItem('');
    };

    const handleRemoveItem = (index) => {
        setGroceryList(groceryList.filter((_, i) => i !== index));
    };

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

    return (
        <SafeAreaView style={styles.safeArea}>
            <FlatList
                ListHeaderComponent={
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
                        <InputWithButton
                            label="Enter grocery item..."
                            value={item}
                            onChangeText={setItem}
                            buttonLabel="Add"
                            onPressButton={handleAddItem}
                        />
                        <Text style={styles.listHeader}>Grocery List</Text>
                    </>
                }
                data={groceryList}
                renderItem={({ item, index }) => (
                    <View style={styles.listItem}>
                        <Text style={styles.itemText}>{item}</Text>
                        <TouchableOpacity onPress={() => handleRemoveItem(index)}>
                            <AntDesign name="delete" size={24} color="red" />
                        </TouchableOpacity>
                    </View>
                )}
                keyExtractor={(item, index) => index.toString()}
                ListFooterComponent={
                    <>
                        <TouchableOpacity style={styles.button} onPress={handleGenerateRoute}>
                            <Text style={styles.buttonText}>Generate Route</Text>
                        </TouchableOpacity>
                        <Text style={styles.listHeader}>Aisles</Text>
                        <FlatList
                            data={aisles}
                            renderItem={({ item }) => (
                                <View style={styles.listItem}>
                                    <Text style={styles.aisleName}>{item.aisleName}</Text>
                                    {item.items.map((itemName, index) => (
                                        <Text key={index} style={styles.itemText}>{itemName}</Text>
                                    ))}
                                </View>
                            )}
                            keyExtractor={(item, index) => index.toString()}
                        />
                        <StatusBar style="auto" />
                    </>
                }
            />
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