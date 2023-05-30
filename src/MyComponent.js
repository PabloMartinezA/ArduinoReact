import React, { useEffect, useState } from 'react';
import { Line } from 'react-chartjs-2';

const MyComponent = () => {
  const [data, setData] = useState([]);
  console.log('Received data:', data)

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = () => {
    fetch('http://localhost:5000/data', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Cache-Control': 'no-cache', // Agrega esta cabecera para evitar la caché
      },
      body: JSON.stringify({}),
    })
      .then((response) => {
        console.log('Received response:', response);
        return response.json();
      })
      .then((data) => {
        const ledValue = data.ledValue;
        setData((prevData) => [...prevData.slice(-9), ledValue]);
        setTimeout(fetchData, 20000);
      })
      .catch((error) => {
        console.error('Error al obtener los datos:', error);
      });
  };
  
  

  const chartData = {
    labels: data.length > 0 ? data.map((_, index) => `Dato ${index + 1}`) : [],
    datasets: [
      {
        label: 'Valor del LED',
        data: data,
        fill: false,
        borderColor: 'rgb(75, 192, 192)',
        tension: 0.1,
      },
    ],
  };

  return (
    <div>
      <h2>Gráfico del valor del LED</h2>
      <Line data={chartData} />
    </div>
  );
};

export default MyComponent;
