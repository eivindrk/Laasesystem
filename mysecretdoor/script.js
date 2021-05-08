const lockBtn = document.getElementById('lockbutton');
const unlockBtn = document.getElementById('unlockbutton2');
const kode = document.getElementById('kode');

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
        //xhttp.setRequestHeader('Access-Control-Allow-Headers', '*');
        //xhttp.setRequestHeader('Access-Control-Allow-Origin', '*'); // Prøv dette
        xhr.send(JSON.stringify(data));
        console.log(JSON.stringify(data));
    });
    return promise;
};

const getData = () => {
    sendHttpRequest('GET', 'http://46.9.150.53/close');
};

const sendData = () => {
    sendHttpRequest('POST', 'http://46.9.150.53/open', {
        doorcode: "gullsmidige"
    });
}


const test = lockBtn.addEventListener('click', getData);
const test2 = unlockBtn.addEventListener('click', sendData);

