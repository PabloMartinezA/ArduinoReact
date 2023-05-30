import React, { useEffect, useState } from 'react';

const MyComponent = () => {
  const [data, setData] = useState('');

  useEffect(() => {
    fetchData();
  }, []);
  

  const fetchData = () => {
    fetch('http://localhost:5000/data')
      .then(response => response.json())
      .then(data => {
        console.log(data);
        setData(data.message);
        console.log(data.message);
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
