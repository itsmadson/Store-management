
## **Store Management**

### **Overview**
This project involves the development of a store management system implemented in two different frameworks: a console application and an Electron application. The Electron application provides a graphical user interface (GUI) using web technologies (HTML, CSS, JavaScript) and is synchronized with the console application through a shared `inventory.txt` file. Any changes made in one interface are reflected in the other.

![image](https://github.com/itsmadson/Store-management/assets/67187216/b3f559f0-6a8e-4163-b632-400f61ffbda1)



### **Getting Started**
1. **Clone the repository**:
   ```bash
   git clone https://github.com/itsmadson/Store-management.git
   ```
2. **Navigate to the project directory**:
   ```bash
   cd Store-management
   ```
3. **Open the project in VS Code**:
   ```bash
   code .
   ```

4. **Console Version**:
   - You will find the `store.cpp` file which contains the console version of the program. You can compile and run this file to test the console version.

5. **Electron Version**:
   - After opening the project in VS Code, install the required Node.js packages:
     ```bash
     npm install
     ```
   - Start the Electron application:
     ```bash
     npm start
     ```

### **Project Details**

#### **1. Console Version:**
   - **Load Inventory**: The program starts by loading the `inventory.txt` file using the `load_inventory` function, which reads the products into a defined `Product` structure.
   - **Display Inventory**: Products are displayed in the terminal line by line using the `display_inventory` function.
   - **User Interactions**: The user is prompted to edit products or create an invoice:
     - **Edit Products**: Options include adding, editing, or deleting products.
       - **Add Product**: Prompts the user for product code, name, quantity, and price, then adds the product to the inventory and saves it.
       - **Edit Product**: Prompts the user for the product code to edit, searches the inventory, and allows the user to update the quantity and price if the product is found.
       - **Delete Product**: Prompts the user for the product code to delete, searches the inventory, and removes the product if found.
     - **Create Cart**: The user is prompted to enter product codes or names to add to the cart. The total price is calculated, and a receipt is generated with the customer's name and the total amount. If no products are found, a message indicating an empty cart is displayed.

#### **2. Electron Version:**
   - **Framework**: Built using the Electron framework which allows for the creation of desktop applications with web technologies.
   - **UI Design**: HTML is used to define the structure including inventory tables, text inputs, and buttons. CSS provides the styling, and JavaScript handles the functionality.
   - **Functionality**: The same functions as the console version are implemented in `renderer.js` to ensure the GUI interacts with `inventory.txt` in the same way as the console application. Both versions read and write to the same file, ensuring synchronization.

### **Conclusion**
The project successfully demonstrates a store management system with both console and GUI interfaces, synchronized through a common inventory file. The Electron framework allowed for the use of web technologies to create a user-friendly interface, while the console version provided a straightforward implementation.


