import * as SecureStore from 'expo-secure-store';

// Function to set a cookie (store data securely)
export async function setCookie(key, value) {
    try {
        await SecureStore.setItemAsync(key, value);
        console.log(`Cookie set: ${key}`);
    } catch (error) {
        console.error(`Error setting cookie ${key}:`, error);
    }
}

// Function to get a cookie (retrieve stored data)
export async function getCookie(key) {
    try {
        const value = await SecureStore.getItemAsync(key);
        console.log(`Cookie retrieved: ${key}`);
        return value;
    } catch (error) {
        console.error(`Error getting cookie ${key}:`, error);
        return null;
    }
}

// Function to delete a cookie (remove stored data)
export async function deleteCookie(key) {
    try {
        await SecureStore.deleteItemAsync(key);
        console.log(`Cookie deleted: ${key}`);
    } catch (error) {
        console.error(`Error deleting cookie ${key}:`, error);
    }
}

// Function to list all cookies (for debugging purposes)
export async function listCookies() {
    try {
        const keys = await SecureStore.getAllKeysAsync();
        console.log('All cookies:', keys);
        return keys;
    } catch (error) {
        console.error('Error listing cookies:', error);
        return [];
    }
}

/*
* This file provides utility functions to manage cookies (securely store data) using Expo SecureStore.
*
* The functions provided are:
* - setCookie(key, value): Stores a value securely under the given key.
* - getCookie(key): Retrieves the value stored under the given key.
* - deleteCookie(key): Deletes the value stored under the given key.
* - listCookies(): Lists all stored keys (for debugging purposes).
*
* Error handling is included to ensure any issues with secure storage are logged to the console.
*
* Placeholders:
* - To add new functionalities, define new functions and add corresponding error handling.
* - To handle more complex data, consider serializing objects to JSON before storing and parsing them after retrieval.
*
* Example of how to use these functions:
*
* // Setting a cookie
* await setCookie('userToken', 'abc123');
*
* // Getting a cookie
* const userToken = await getCookie('userToken');
*
* // Deleting a cookie
* await deleteCookie('userToken');
*
* // Listing all cookies (for debugging purposes)
* const allCookies = await listCookies();
*
* These functions help in securely storing user data, such as authentication tokens, preferences, and other sensitive information.
*/
