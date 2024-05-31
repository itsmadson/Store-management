const fs = require('fs');
const { ipcRenderer } = require('electron');

let inventoryFile = '';
let inventory = [];

// Listen for the inventory file path from the main process
ipcRenderer.on('inventory-file-path', (event, filePath) => {
  inventoryFile = filePath;
  console.log('Using inventory file:', inventoryFile);
  loadInventory();
});

// Load inventory from the file
function loadInventory() {
  try {
    const data = fs.readFileSync(inventoryFile, 'utf8');
    inventory = data.trim().split('\n')
      .filter(line => line.trim() !== '')
      .map(line => {
        const [code, ...nameParts] = line.trim().split(/\s+/);
        const name = nameParts.slice(0, -2).join(' ');
        const quantity = parseInt(nameParts[nameParts.length - 2]);
        const price = parseFloat(nameParts[nameParts.length - 1]);
        return { code, name, quantity, price };
      });
    displayInventory();
  } catch (err) {
    console.error('Error reading inventory:', err);
    inventory = [];
  }
}

// Save inventory to the file
function saveInventory() {
  try {
    const data = inventory.map(p => `${p.code} ${p.name} ${p.quantity} ${p.price}`).join('\n');
    fs.writeFileSync(inventoryFile, data, 'utf8');
    console.log('Inventory saved:', data);
  } catch (err) {
    console.error('Error saving inventory:', err);
  }
}

// Display the inventory in the table
function displayInventory() {
  const tbody = document.querySelector('#inventoryTable tbody');
  tbody.innerHTML = '';
  inventory.forEach(p => {
    const tr = document.createElement('tr');
    tr.innerHTML = `
      <td>${p.code}</td>
      <td>${p.name}</td>
      <td>${p.quantity}</td>
      <td>$${p.price.toFixed(2)}</td>
      <td>
        <button onclick="editProduct('${p.code}')">Edit</button>
        <button onclick="removeProduct('${p.code}')">Remove</button>
      </td>
    `;
    tbody.appendChild(tr);
  });
}

// Add or update a product in the inventory
function addProduct() {
  const code = document.getElementById('productCode').value;
  const name = document.getElementById('productName').value;
  const quantity = parseInt(document.getElementById('productQuantity').value) || 0;
  const price = parseFloat(document.getElementById('productPrice').value) || 0;

  if (!code || !name) {
    alert('Code and Name are required!');
    return;
  }

  const index = inventory.findIndex(p => p.code === code);
  if (index !== -1) {
    inventory[index] = { code, name, quantity, price };
    alert('Product updated!');
  } else {
    inventory.push({ code, name, quantity, price });
    alert('Product added!');
  }

  saveInventory();
  displayInventory();
  document.getElementById('productForm').reset();
}

// Edit an existing product
function editProduct(code) {
  const p = inventory.find(p => p.code === code);
  if (p) {
    document.getElementById('productCode').value = p.code;
    document.getElementById('productName').value = p.name;
    document.getElementById('productQuantity').value = p.quantity;
    document.getElementById('productPrice').value = p.price;
  }
}

// Remove a product from the inventory
function removeProduct(code) {
  const index = inventory.findIndex(p => p.code === code);
  if (index !== -1) {
    inventory.splice(index, 1);
    saveInventory();
    displayInventory();
  }
}

// Create a new cart and display the invoice
function createCart() {
  const cart = [];
  let totalPrice = 0;

  const customerName = prompt('Enter customer name:') || 'Guest';

  while (true) {
    const input = prompt('Enter product code or name (or "done" to finish):');
    if (!input || input.toLowerCase() === 'done') break;

    const product = inventory.find(p => p.code === input || p.name.toLowerCase() === input.toLowerCase());
    if (product) {
      const qty = parseInt(prompt(`Enter quantity for ${product.name} (available: ${product.quantity}):`)) || 0;
      if (qty > 0 && qty <= product.quantity) {
        cart.push({ ...product, quantity: qty });
        totalPrice += product.price * qty;
      } else {
        alert(`Invalid quantity. Available: ${product.quantity}`);
      }
    } else {
      alert('Product not found.');
    }
  }

  if (cart.length > 0) {
    let invoiceHtml = `<h3>Invoice for ${customerName}</h3>`;
    invoiceHtml += '<table><tr><th>Code</th><th>Name</th><th>Qty</th><th>Price</th><th>Total</th></tr>';
    cart.forEach(item => {
      const itemTotal = item.price * item.quantity;
      invoiceHtml += `<tr>
        <td>${item.code}</td>
        <td>${item.name}</td>
        <td>${item.quantity}</td>
        <td>$${item.price.toFixed(2)}</td>
        <td>$${itemTotal.toFixed(2)}</td>
      </tr>`;

      // Update inventory quantity
      const inventoryItem = inventory.find(p => p.code === item.code);
      if (inventoryItem) {
        inventoryItem.quantity -= item.quantity;
      }
    });
    invoiceHtml += `</table><p>Total Price: $${totalPrice.toFixed(2)}</p>`;
    
    document.getElementById('invoiceSection').innerHTML = invoiceHtml;
    document.getElementById('invoiceSection').style.display = 'block';
    
    // Save updated inventory
    saveInventory();
    // Refresh the inventory display
    displayInventory();
  } else {
    alert('Cart is empty.');
  }
}

// Event listeners setup
window.onload = () => {
  document.getElementById('createCartBtn').onclick = createCart;
  document.getElementById('darkModeToggle').onclick = () => {
    document.body.classList.toggle('dark-mode');
  };
};
