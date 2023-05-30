from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

@app.route('/data', methods=['POST'])
def get_data():
    data = request.get_json()
    led_value = data.get('ledValue', 0.0)

    response = {'ledValue': led_value}
    print(response)

    return jsonify(response)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
