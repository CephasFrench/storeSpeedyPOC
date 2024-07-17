import React from 'react';
import { View, TextInput, Button, StyleSheet } from 'react-native';

export default function InputWithButton({ label, value, onChangeText, buttonLabel, onPressButton }) {
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
                color="#ff0000"
            />
        </View>
    );
}

const styles = StyleSheet.create({
    inputContainer: {
        flexDirection: 'row',
        width: '100%',
        alignItems: 'center',
        marginBottom: 10,
        borderColor: '#000000',
        borderWidth: 1,
        borderRadius: 5,
    },
    input: {
        height: 40,
        flex: 1,
        borderWidth: 0,
        padding: 10,
        backgroundColor: '#ffffff',
    },
});