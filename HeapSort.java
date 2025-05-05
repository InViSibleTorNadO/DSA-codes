import java.util.Scanner;

public class HeapSort {

    // The heapify function is used to maintain the heap property. 
    // It ensures that the subtree rooted at index 'i' is a heap.
    public static void heapify(int[] arr, int i, int n) {
        int smallest = i;              // Assume the current node is the smallest
        int l = 2 * i + 1;             // Left child index
        int r = 2 * i + 2;             // Right child index

        // If left child exists and is smaller than the current smallest, update smallest
        if (l < n && arr[l] < arr[smallest]) {
            smallest = l;
        }

        // If right child exists and is smaller than the current smallest, update smallest
        if (r < n && arr[r] < arr[smallest]) {
            smallest = r;
        }

        // If the smallest value is not the root, swap and recursively heapify the affected subtree
        if (smallest != i) {
            int tmp = arr[i];          // Swap current node with smallest child
            arr[i] = arr[smallest];
            arr[smallest] = tmp;
            heapify(arr, smallest, n); // Recursively heapify the affected subtree
        }
    }

    // The heapSort function first builds the heap, then extracts elements one by one.
    public static void heapSort(int[] arr, int n) {
        // Build the heap by calling heapify on all non-leaf nodes
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, i, n);  // Start from the last non-leaf node and move upwards
        }

        // Extract elements from the heap one by one
        for (int i = n - 1; i >= 0; i--) {
            // Swap the root (maximum element) with the last element in the heap
            int tmp = arr[0];
            arr[0] = arr[i];
            arr[i] = tmp;

            // Call heapify to maintain the heap property after the swap
            heapify(arr, 0, i); // After each swap, reduce the size of the heap by 1
        }
    }

    // Main function to drive the program and interact with the user
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Infinite loop to keep the menu running
        while (true) {
            System.out.print("\nMENU:\n1. HEAP SORT\n2. EXIT\n");
            System.out.print("ENTER YOUR CHOICE: ");
            int ch = scanner.nextInt();  // Get user choice

            // Switch case for menu options
            switch (ch) {
                // If the user selects heap sort
                case 1: {
                    // Get the number of elements for the array
                    System.out.println("Enter no. of elements: ");
                    int n = scanner.nextInt();

                    // Initialize the array with user-provided elements
                    int[] arr = new int[n];
                    System.out.println("Enter the array elements: ");
                    for (int i = 0; i < n; i++) {
                        arr[i] = scanner.nextInt();  // Read each element
                    }

                    // Call heapSort function to sort the array
                    heapSort(arr, n);

                    // Print the sorted array
                    System.out.print("Sorted Array: ");
                    for (int i = 0; i < n; i++) {
                        System.out.print(arr[i] + " ");  // Print each element of the sorted array
                    }
                    System.out.println();  // Print a newline after the array
                    break;  // Exit the heap sort case
                }
                // If the user selects exit
                case 2: {
                    scanner.close();  // Close the scanner
                    System.exit(0);   // Exit the program
                }
            }
        }
    }
}