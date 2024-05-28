const { app, BrowserWindow } = require('electron');

app.on('ready', () => {
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 750,
    webPreferences: {
      nodeIntegration: true
    }
  });

  mainWindow.loadFile('src/frontend/main.html');
});
