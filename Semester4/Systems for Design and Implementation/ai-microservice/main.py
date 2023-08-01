from transformers import DistilBertTokenizer, DistilBertModel, pipeline
import torch
from flask import Flask, make_response, request


app = Flask(__name__)


@app.route("/", methods=['POST'])
def get_ai_response():
    question_answerer = pipeline("question-answering", model='distilbert-base-cased-distilled-squad')
    
    json = request.json
    
    output = question_answerer(question=json.get("question"), context=json.get("text"))

# Get the output embeddings

    response = make_response(str(output['answer']), 200)
    response.mimetype = "text/plain"
    return response

