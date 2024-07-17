import * as SecureStore from 'expo-secure-store';

export async function setCookie(key, value) {
    await SecureStore.setItemAsync(key, value);
}

export async function getCookie(key) {
    return await SecureStore.getItemAsync(key);
}

export async function deleteCookie(key) {
    await SecureStore.deleteItemAsync(key);
}