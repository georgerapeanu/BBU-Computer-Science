FROM huggingface/transformers-cpu:4.18.0

WORKDIR /app
COPY ./requirements.txt .
COPY ./__init__.py .
RUN python3 -m pip install --upgrade pip
RUN pip3 install -r requirements.txt
RUN python3 __init__.py
EXPOSE 5000
ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8i
ENV FLASK_APP main
COPY ./main.py .
CMD ["flask", "run", "--host=0.0.0.0", "--port=5000"]
