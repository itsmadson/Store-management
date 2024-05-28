const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const fs = require('fs');

let mainWindow;

function createWindow () {
    mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            nodeIntegration: true,
            contextIsolation: false
        }
    });

    mainWindow.loadFile('src/frontend/index.html');
}

app.whenReady().then(() => {
    createWindow();

    app.on('activate', function () {
        if (BrowserWindow.getAllWindows().length === 0) createWindow();
    });
});

app.on('window-all-closed', function () {
    if (process.platform !== 'darwin') app.quit();
});

let products = [];

ipcMain.handle('load-products', async () => {
    const data = fs.readFileSync('products.json', 'utf-8');
    products = JSON.parse(data);
    return products;
});

ipcMain.handle('save-product', async (event, product) => {
    const existingProductIndex = products.findIndex(p => p.code === product.code);
    if (existingProductIndex !== -1) {
        products[existingProductIndex] = product;
    } else {
        products.push(product);
    }
    fs.writeFileSync('products.json', JSON.stringify(products));
});

ipcMain.handle('delete-product', async (event, code) => {
    products = products.filter(p => p.code !== code);
    fs.writeFileSync('products.json', JSON.stringify(products));
});

ipcMain.handle('purchase-products', async (event, cart) => {
    cart.forEach(item => {
        const product = products.find(p => p.code === item.code);
        if (product) {
            product.quantity -= item.quantity;
        }
    });
    fs.writeFileSync('products.json', JSON.stringify(products));
});

try {
    require('./build/Release/store.node');
    console.log('C++ addon loaded successfully');
  } catch (err) {
    console.error('Failed to load C++ addon', err);
  }