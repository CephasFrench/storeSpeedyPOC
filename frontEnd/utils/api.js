import * as SecureStore from 'expo-secure-store';

// Fetch the grocery list from the backend
export const fetchGroceryList = async (SERVER_URL, userId, location, setGroceryList, setLoading, setError) => {
    try {
        const response = await fetch(`${SERVER_URL}/grocery_list/${userId}/${location}`);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const data = await response.json();
        console.log('Fetched grocery list:', data);

        // Ensure the data is in the correct format
        if (data.items && Array.isArray(data.items)) {
            setGroceryList(data.items);
        } else if (Array.isArray(data)) {
            setGroceryList(data);
        } else {
            throw new Error('Invalid items data. Expected an array of items.');
        }
    } catch (error) {
        console.error('Error fetching grocery list:', error);
        setError('Failed to load items. Please try again later.');
    } finally {
        setLoading(false);
    }
};

// Update the grocery list in the backend
export const updateGroceryList = async (SERVER_URL, userId, location, updatedGroceryList) => {
    const updatedData = { items: updatedGroceryList }; // Update this structure as needed
    try {
        const response = await fetch(`${SERVER_URL}/update_grocery_list/${userId}/${location}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(updatedData),
        });
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        console.log("Grocery list updated successfully.");
    } catch (error) {
        console.error('Error updating data:', error);
        throw new Error('Failed to update grocery list.');
    }
};

// Check if HEB sells the item before adding to the list
export const checkItemAvailability = async (SERVER_URL, item) => {
    const response = await fetch(`${SERVER_URL}/check_item`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ item }),
    });

    if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
    }

    const data = await response.text(); // Expect plain text "YES" or "NO"
    return data;
};

// Update the server with the new location whenever it changes
export const updateLocation = async (SERVER_URL, location, setError) => {
    try {
        await fetch(`${SERVER_URL}/update_location`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ location }),
        });
    } catch (error) {
        console.error('Error updating location:', error);
        setError("Failed to update location.");
    }
};

// Fetch developer mode from secure storage
export const fetchDeveloperMode = async (setIsDeveloper) => {
    const storedIsDeveloper = await SecureStore.getItemAsync('isDeveloper');
    setIsDeveloper(storedIsDeveloper === 'true');
};
