import React from 'react';
import { FlatList, View, Text, StyleSheet } from 'react-native';
import { BOOLEAN_VALUES } from '/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd/config';

// AisleList component to display aisles and their items
export default function AisleList({ aisles }) {
    // Check if aisles prop is valid
    if (!aisles || !Array.isArray(aisles)) {
        console.error('Invalid aisles data. Expected an array of aisles.');
        return <Text style={styles.errorText}>Failed to load aisles. Please try again later.</Text>;
    }

    return (
        BOOLEAN_VALUES.SHOW_AISLES && (
            <FlatList
                style={styles.list}
                data={aisles}
                renderItem={({ item }) => (
                    <View style={styles.listItem}>
                        <Text style={styles.aisleName}>{item.aisleName}</Text>
                        {Array.isArray(item.items) ? (
                            item.items.map((itemName, index) => (
                                <Text key={index} style={styles.itemText}>{itemName}</Text>
                            ))
                        ) : (
                            <Text style={styles.itemText}>No items available</Text>
                        )}
                    </View>
                )}
                keyExtractor={(_, index) => index.toString()}
            />
        )
    );
}

// Styles for the AisleList component
const styles = StyleSheet.create({
    list: {
        width: '100%',
        marginBottom: 20,
    },
    listItem: {
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
    aisleName: {
        fontSize: 18,
        fontWeight: 'bold',
        color: '#1d3557',
    },
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});

/*
* This file defines the AisleList component, which renders a list of aisles and their items using React Native's FlatList.
* 
* The component expects a prop called 'aisles', which should be an array of objects. Each object represents an aisle and should have the following structure:
* {
*   aisleName: 'Aisle Name', // string
*   items: ['item1', 'item2'] // array of strings
* }
* 
* If the 'aisles' prop is invalid, an error message will be displayed instead of the list.
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
* <AisleList aisles={aislesData} />
* 
* Here, 'aislesData' should be an array of aisle objects as described above.
*/
