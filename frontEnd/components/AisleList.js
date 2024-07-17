import React from 'react';
import { FlatList, View, Text, StyleSheet } from 'react-native';

export default function AisleList({ aisles }) {
    return (
        <FlatList
            style={styles.list}
            data={aisles}
            renderItem={({ item }) => (
                <View style={styles.listItem}>
                    <Text style={styles.aisleName}>{item.aisleName}</Text>
                    {item.items.map((itemName, index) => (
                        <Text key={index} style={styles.itemText}>{itemName}</Text>
                    ))}
                </View>
            )}
            keyExtractor={(_, index) => index.toString()}
        />
    );
}

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
});