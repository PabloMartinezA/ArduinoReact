import React, { useEffect, useState } from 'react';

const MyComponent = () => {
  const [data, setData] = useState('');

  useEffect(() => {
    fetchData();
  }, []);
  
  const fetchData = () => {
    fetch('http://localhost:5000/data', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({}),
    })
      .then(response => response.json())
      .then(data => {
        console.log(data);
        setData(data.message); // Guarda el mensaje recibido en el estado 'data'
      })
      .catch(error => {
        console.error('Error:', error);
      });
  };
  
  return (
    <div>
      <h1>Componente de React</h1>
      {data ? <p>{data}</p> : null} {/* Muestra el mensaje si está disponible */}
    </div>
  );
};

export default MyComponent;
