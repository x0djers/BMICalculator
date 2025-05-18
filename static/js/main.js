document.addEventListener('DOMContentLoaded', () => {
    const imperialBtn = document.getElementById('imperialBtn');
    const metricBtn   = document.getElementById('metricBtn');
    const weightUnit  = document.getElementById('weightUnit');
    const heightUnit  = document.getElementById('heightUnit');
    const weightInput = document.getElementById('weightInput');
    const heightInput = document.getElementById('heightInput');

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
