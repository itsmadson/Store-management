const { ipcRenderer } = require('electron');

document.addEventListener('DOMContentLoaded', () => {
    const productForm = document.getElementById('productForm');
    const productTableBody = document.getElementById('productTable').getElementsByTagName('tbody')[0];
    const cartTableBody = document.getElementById('cartTable').getElementsByTagName('tbody')[0];
    const purchaseBtn = document.getElementById('purchaseBtn');

    // Load products from file and display them
    ipcRenderer.invoke('load-products').then(products => {
        products.forEach(product => addProductRow(product));
    });

    // Handle product form submission
    productForm.addEventListener('submit', (event) => {
        event.preventDefault();

        const code = parseInt(document.getElementById('code').value);
        const name = document.getElementById('name').value;
        const quantity = parseInt(document.getElementById('quantity').value);
        const price = parseFloat(document.getElementById('price').value);

        const product = { code, name, quantity, price };

        ipcRenderer.invoke('save-product', product).then(() => {
            addProductRow(product);
        });

        productForm.reset();
    });

    // Handle purchase button click
    purchaseBtn.addEventListener('click', () => {
        const cart = [];
        for (let i = 0; i < cartTableBody.rows.length; i++) {
            const row = cartTableBody.rows[i];
            const code = parseInt(row.cells[0].innerText);
            const quantity = parseInt(row.cells[2].innerText);
            cart.push({ code, quantity });
        }

        ipcRenderer.invoke('purchase-products', cart).then(() => {
            // Refresh product list and clear cart
            productTableBody.innerHTML = '';
            cartTableBody.innerHTML = '';
            ipcRenderer.invoke('load-products').then(products => {
                products.forEach(product => addProductRow(product));
            });
        });
    });

    function addProductRow(product) {
        const row = productTableBody.insertRow();
        row.insertCell(0).innerText = product.code;
        row.insertCell(1).innerText = product.name;
        row.insertCell(2).innerText = product.quantity;
        row.insertCell(3).innerText = product.price.toFixed(2);
        const actionsCell = row.insertCell(4);

        const editButton = document.createElement('button');
        editButton.innerText = 'Edit';
        editButton.addEventListener('click', () => editProduct(product));
        actionsCell.appendChild(editButton);

        const deleteButton = document.createElement('button');
        deleteButton.innerText = 'Delete';
        deleteButton.addEventListener('click', () => deleteProduct(product.code));
        actionsCell.appendChild(deleteButton);
    }

    function editProduct(product) {
        document.getElementById('code').value = product.code;
        document.getElementById('name').value = product.name;
        document.getElementById('quantity').value = product.quantity;
        document.getElementById('price').value = product.price;
    }

    function deleteProduct(code) {
        ipcRenderer.invoke('delete-product', code).then(() => {
            for (let i = 0; i < productTableBody.rows.length; i++) {
                const row = productTableBody.rows[i];
                if (parseInt(row.cells[0].innerText) === code) {
                    productTableBody.deleteRow(i);
                    break;
                }
            }
        });
    }
});
