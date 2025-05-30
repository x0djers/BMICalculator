document.addEventListener('DOMContentLoaded', function () {
    let bmi = parseFloat(localStorage.getItem('bmi'));
    if (isNaN(bmi)) bmi = 0;

    const rootStyles = getComputedStyle(document.documentElement);
    const getVar = (name) => rootStyles.getPropertyValue(name).trim();

    const COLORS = {
        underweight: getVar('--bmi-blue'),
        normal: getVar('--bmi-green'),
        overweight: getVar('--bmi-orange'),
        obese: getVar('--bmi-red')
    };

    const label = document.getElementById('label');
    const desc = document.getElementById('desc');
    const indicator = document.getElementById('indicator');

    const categories = [
        {
            limit: 18.5,
            color: COLORS.underweight,
            text: 'Недостаточный вес',
            desc: 'Ваш ИМТ ниже нормы. Рекомендуется улучшить питание.'
        },
        {
            limit: 25,
            color: COLORS.normal,
            text: 'Нормальный вес',
            desc: 'Ваш ИМТ в пределах нормы. Продолжайте в том же духе!'
        },
        {
            limit: 30,
            color: COLORS.overweight,
            text: 'Избыточный вес',
            desc: 'Ваш ИМТ превышает норму. Рекомендуется обратить' +
                  'внимание на рацион.'
        },
        {
            limit: Infinity,
            color: COLORS.obese,
            text: 'Ожирение',
            desc: 'Ваш ИМТ значительно превышает норму. ' +
                  'Необходимо проконсультироваться со специалистом.'
        }
    ];

    document.getElementById('bmi').textContent = bmi.toFixed(1);

    const category = categories.find(c => bmi < c.limit);

    label.textContent = category.text;
    label.style.background = category.color;
    desc.textContent = category.desc;

    const percent = Math.min((bmi / 40) * 100, 100);
    indicator.style.left = `${percent}%`;
});
