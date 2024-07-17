import React from 'react';
import { FlatList, View, Text, TouchableOpacity, StyleSheet } from 'react-native';
import { AntDesign } from '@expo/vector-icons';
import { BOOLEAN_VALUES } from '/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd/config';

// GroceryList component to display a list of grocery items
export default function GroceryList({ items, onRemoveItem }) {
    // Check if items prop is valid
    if (!items || !Array.isArray(items)) {
        console.error('Invalid items data. Expected an array of items.');
        return <Text style={styles.errorText}>Failed to load items. Please try again later.</Text>;
    }

    // Check if onRemoveItem prop is a valid function
    if (typeof onRemoveItem !== 'function') {
        console.error('Invalid onRemoveItem handler. Expected a function.');
        return <Text style={styles.errorText}>Failed to load items. Please try again later.</Text>;
    }

    return (
        BOOLEAN_VALUES.SHOW_ITEM_INPUT && (
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
        )
    );
}

// Styles for the GroceryList component
const styles = StyleSheet.create({
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
        borderColor: '#000000',
        borderRadius: 5,
        marginBottom: 10,
    },
    itemText: {
        fontSize: 16,
        color: '#343a40',
    },
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});

/*
* This file defines the GroceryList component, which renders a list of grocery items using React Native's FlatList.
* 
* The component expects two props:
* - 'items': an array of strings, each representing a grocery item.
* - 'onRemoveItem': a function to handle the removal of an item from the list.
* 
* If the 'items' prop is invalid or the 'onRemoveItem' handler is not a function, an error message will be displayed.
*
* Style definitions are provided at the bottom of the file to maintain visual consistency.
*
* Placeholders:
* - To add new functionality or features, you can add new props and their corresponding checks at the top of the component.
* - To handle more complex data structures, update the renderItem function accordingly.
* - For additional styles, update the StyleSheet object as needed.
*
* Example of how to use this component:
* 
* <GroceryList items={groceryItems} onRemoveItem={handleRemoveItem} />
* 
* Here, 'groceryItems' should be an array of strings representing the items, and 'handleRemoveItem' should be a function to handle item removal.
*/
