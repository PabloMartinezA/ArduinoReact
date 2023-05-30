from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})

@app.route('/data', methods=['POST', 'OPTIONS'])
def get_data():
    if request.method == 'OPTIONS':
        return jsonify({'status': 'success'})

    data = request.get_json()
    print('Received data:', data)  # Agrega este mensaje de depuración
    led_value = data.get('ledValue', 0)
    print('Debug2:', data)
    response = {'ledValue': led_value}
    print('Response:', response)  # Agrega este mensaje de depuración

    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)  # Agrega debug=True para obtener información detallada en caso de errores
