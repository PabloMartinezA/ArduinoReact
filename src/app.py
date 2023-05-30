from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

@app.before_request
def before_request():
    if request.method == 'POST' and request.is_json:
        # Si la solicitud es POST y contiene datos en formato JSON, se procesa
        pass  # Aquí puedes realizar las acciones necesarias antes de la solicitud

@app.route('/data', methods=['POST'])
def get_data():
    # Obtiene los datos enviados desde Arduino
    data = request.get_json()
    
    # Obtén el mensaje enviado por Arduino
    message = data.get('data', {}).get('message', '')  # Actualización en esta línea

    # Crea la respuesta con el mensaje recibido
    response = {'message': message}

    print(response)  # Verifica que la respuesta se esté generando correctamente

    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
