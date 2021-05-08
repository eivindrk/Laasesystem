const lockBtn = document.getElementById('lockbutton');
const unlockBtn = document.getElementById('unlockbutton2');
let kode = document.getElementById('kode');


const myForm = document.getElementById('myForm');
myForm.addEventListener('submit', function(e) {
    e.preventDefault();

    const formData = new FormData(this);

    fetch('http://212.251.163.91/open', {
        method: 'post', 
        body: formData
    }).then(function(response) {
        return response.text();
    }).then(function(text) {
        console.log(text);
    }).catch(function (error) {
        console.log(error);
    });
});

const sendHttpRequest = (method, url, data) => {
    const promise = new Promise((resolve, reject) => {
        const xhr = new XMLHttpRequest();
        xhr.open(method, url);
        xhr.responseType = 'json';
        if (data) {
            xhr.setRequestHeader('Content-Type', 'application/json');
        }
        xhr.onload = () => {
            resolve(xhr.response);
        }
        xhr.onerror = () => {
            reject('Error, something went wrong');
        }
        xhr.send(JSON.stringify(data));
        //JSON.stringify(data)
        console.log(JSON.stringify(data));
    });
    return promise;
};

const getData = () => {
    sendHttpRequest('GET', 'http://212.251.163.91/close');
};

const sendData = () => {
    let nyknapp = document.getElementById('kode').value;
    sendHttpRequest('POST', 'http://212.251.163.91/open', {
        doorcode: nyknapp
    });
}


const test = lockBtn.addEventListener('click', getData);
const test2 = unlockBtn.addEventListener('click', sendData);

