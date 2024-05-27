const addon = require('../build/Release/store.node');
const Store = addon.Store;

const store = new Store();

const productList = document.getElementById('product-list').querySelector('ul');
const cartList = document.getElementById('cart').querySelector('ul');
const purchaseBtn = document.getElementById('purchase-btn');

const products = store.products;

products.forEach(product => {
  const li = document.createElement('li');
  li.textContent = `${product.name} - $${product.price} (${product.quantity} remaining)`;
  li.addEventListener('click', () => addToCart(product));
  productList.appendChild(li);
});

const cart = [];

function addToCart(product) {
  cart.push(product);
  renderCart();
  purchaseBtn.disabled = false;
}

function removeFromCart(index) {
  cart.splice(index, 1);
  renderCart();
  purchaseBtn.disabled = cart.length === 0;
}

function renderCart() {
  cartList.innerHTML = '';
  cart.forEach((product, index) => {
    const li = document.createElement('li');
    li.textContent = `${product.name} - $${product.price}`;
    const removeBtn = document.createElement('button');
    removeBtn.textContent = 'Remove';
    removeBtn.addEventListener('click', () => removeFromCart(index));
    li.appendChild(removeBtn);
    cartList.appendChild(li);
  });
}

function purchase() {
  const codes = cart.map(product => [product.code, 1]);
  const total = store.purchase(codes);
  alert(`Purchase completed! Total: $${total}`);
  cart.length = 0;
  renderCart();
  purchaseBtn.disabled = true;
}

purchaseBtn.addEventListener('click', purchase);