const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');

function createWindow() {
  const win = new BrowserWindow({
    width: 650,
    height: 800,
    autoHideMenuBar: true,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false
    }
  });


  win.loadFile('index.html');
  
  // Send the inventory file path to the renderer process
  const inventoryFile = path.join(__dirname, 'inventory.txt');
  win.webContents.on('did-finish-load', () => {
    win.webContents.send('inventory-file-path', inventoryFile);
  });
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit();
});