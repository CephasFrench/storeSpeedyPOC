import React from 'react';
import { FlatList, View, Text, TouchableOpacity, StyleSheet } from 'react-native';
import { AntDesign } from '@expo/vector-icons';

export default function GroceryList({ items, onRemoveItem }) {
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
});