import React from 'react';
import { View, TextInput, Button, StyleSheet, Text } from 'react-native';
import { BOOLEAN_VALUES } from '/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd/config';

// InputWithButton component to display a text input with an associated button
export default function InputWithButton({ label, value, onChangeText, buttonLabel, onPressButton }) {
    // Check if required props are provided and valid
    if (typeof onChangeText !== 'function' || typeof onPressButton !== 'function') {
        console.error('Invalid onChangeText or onPressButton handlers. Expected functions.');
        return <Text style={styles.errorText}>Failed to load input. Please try again later.</Text>;
    }

    if (typeof label !== 'string' || typeof buttonLabel !== 'string') {
        console.error('Invalid label or buttonLabel. Expected strings.');
        return <Text style={styles.errorText}>Failed to load input. Please try again later.</Text>;
    }

    return (
        BOOLEAN_VALUES.SHOW_ITEM_INPUT && (
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
        )
    );
}

// Styles for the InputWithButton component
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
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});

/*
* This file defines the InputWithButton component, which renders a text input field with an associated button.
* 
* The component expects the following props:
* - 'label': a string for the input placeholder text.
* - 'value': the current value of the text input.
* - 'onChangeText': a function to handle text changes in the input.
* - 'buttonLabel': a string for the button text.
* - 'onPressButton': a function to handle button presses.
* 
* If the required props are not provided or invalid, an error message will be displayed.
*
* Style definitions are provided at the bottom of the file to maintain visual consistency.
*
* Placeholders:
* - To add new functionality or features, you can add new props and their corresponding checks at the top of the component.
* - To handle more complex interactions, update the TextInput and Button handlers accordingly.
* - For additional styles, update the StyleSheet object as needed.
*
* Example of how to use this component:
* 
* <InputWithButton
*   label="Enter text"
*   value={inputValue}
*   onChangeText={setInputValue}
*   buttonLabel="Submit"
*   onPressButton={handlePress}
* />
* 
* Here, 'inputValue' should be a state variable representing the input value, 'setInputValue' should be the state setter function, and 'handlePress' should be the function to handle button presses.
*/
