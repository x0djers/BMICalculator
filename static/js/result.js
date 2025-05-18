document.addEventListener('DOMContentLoaded', function () {
    let bmi = 0;

    const rootStyles = getComputedStyle(document.documentElement);
    const getVar = (name) => rootStyles.getPropertyValue(name).trim();

    const COLORS = {
        underweight: getVar('--bmi-blue'),
        normal: getVar('--bmi-green'),
        overweight: getVar('--bmi-orange'),
        obese: getVar('--bmi-red')
    };

    document.getElementById('bmi').textContent = bmi.toFixed(1);

    const label = document.getElementById('label');
    const desc = document.getElementById('desc');
    const indicator = document.getElementById('indicator');

    let color, text, description, percent;

    if (bmi < 18.5) {
        color = COLORS.underweight;
        text = 'Недостаточный вес';
        description = 'Ваш ИМТ ниже нормы. Рекомендуется улучшить питание.';
    } else if (bmi < 25) {
        color = COLORS.normal;
        text = 'Нормальный вес';
        description = 'Ваш ИМТ в пределах нормы. Продолжайте в том же духе!';
    } else if (bmi < 30) {
        color = COLORS.overweight;
        text = 'Избыточный вес';
        description = 'Ваш ИМТ превышает норму. Рекомендуется обратить внимание на рацион.';
    } else {
        color = COLORS.obese;
        text = 'Ожирение';
        description = 'Ваш ИМТ значительно превышает норму. Необходимо проконсультироваться со специалистом.';
    }

    percent = Math.min((bmi / 40) * 100, 100);

    label.textContent = text;
    label.style.background = color;
    desc.textContent = description;
    indicator.style.left = `${percent}%`;
});
