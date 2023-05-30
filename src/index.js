import React from 'react';
import ReactDOM from 'react-dom';
import { Chart } from 'chart.js';
import { registerables } from 'chart.js/auto';
import App from './App';

Chart.register(...registerables);

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
);
