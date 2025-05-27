document.addEventListener('DOMContentLoaded', () => {
    const imperialBtn = document.getElementById('imperialBtn');
    const metricBtn   = document.getElementById('metricBtn');
    const weightUnit  = document.getElementById('weightUnit');
    const heightUnit  = document.getElementById('heightUnit');
    const weightInput = document.getElementById('weightInput');
    const heightInput = document.getElementById('heightInput');
    const errorMessage = document.getElementById("errorMessage");
    const calculateBtn = document.querySelector(".calculate-btn");

    imperialBtn.addEventListener('click', () => {
        imperialBtn.classList.add('active');
        metricBtn.classList.remove('active');
        weightUnit.textContent = 'lbs';
        heightUnit.textContent = 'in';
    });

    metricBtn.addEventListener('click', () => {
        metricBtn.classList.add('active');
        imperialBtn.classList.remove('active');
        weightUnit.textContent = 'kg';
        heightUnit.textContent = 'cm';
    });

    weightInput.addEventListener('click', () => {
        errorMessage.classList.remove('visible');
    })

    heightInput.addEventListener('click', () => {
        errorMessage.classList.remove('visible');
    })

    calculateBtn.addEventListener("click", async function () {
        const weight = parseFloat(weightInput.value);
        const height = parseFloat(heightInput.value);
        const units = imperialBtn.classList.contains('active') ? 'imperial' : 'metric';

        if (isNaN(weight) || weight <= 0 || isNaN(height) || height <= 0) {
            errorMessage.classList.add('visible');
        } else {
            errorMessage.classList.remove('visible');
        }
            try {
                const response = await fetch('/api/bmi', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({ height, weight, units })
                });

                if (!response.ok) {
                    throw new Error('Произошла внутренняя ошибка сервера.');
                }

                const data = await response.json();
                const bmi = data.bmi;

                localStorage.setItem('bmi', bmi);

                window.location.href = '/result';

            } catch (err) {
                errorMessage.textContent = err.message;
                errorMessage.classList.add('visible');
            }
    });

    function blockInvalidChars(event) {
        const allowedKeys = [
            '0','1','2','3','4','5','6','7','8','9',
            'Backspace', 'Delete', 'ArrowLeft', 'ArrowRight', 'Tab', 'Enter'
        ];

        if (!(event.ctrlKey || event.metaKey) && !allowedKeys.includes(event.key)) {
            event.preventDefault();
        }
    }

    weightInput.addEventListener('keydown', blockInvalidChars);
    heightInput.addEventListener('keydown', blockInvalidChars);
});
