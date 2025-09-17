document.addEventListener('DOMContentLoaded', function () {

    function disableButtons(container) {
        const buttons = container.querySelectorAll('button');
        buttons.forEach(button => button.disabled = true);
    }

    let correctAnswers = 0; // Counter for correct answers
    const totalQuestions = 3; // Update this if you add more questions


    let corrects = document.querySelectorAll('.correct');
    for (let i = 0; i < corrects.length; i++) {
        corrects[i].addEventListener('click', function () {
            corrects[i].style.backgroundColor = 'green';
            const container = corrects[i].parentElement;
            container.querySelector('.feedback').innerHTML = 'Correct!';
            disableButtons(container);
            correctAnswers++;
            checkIfAllCorrect();
        });
    }


    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function () {
            incorrects[i].style.backgroundColor = 'red';
            const container = incorrects[i].parentElement;
            container.querySelector('.feedback').innerHTML = 'Incorrect';
            disableButtons(container);
        });
    }


    function checkIfAllCorrect() {
        if (correctAnswers === totalQuestions) {
            document.getElementById('win-message').style.display = 'block'; 
        }
    }


    document.getElementById('restart-btn').addEventListener('click', function () {
        const allButtons = document.querySelectorAll('.correct, .incorrect');
        const feedbacks = document.querySelectorAll('.feedback');
        correctAnswers = 0; // Reset the correct answers counter

        allButtons.forEach(button => {
            button.disabled = false;
            button.style.backgroundColor = '';
        });

        feedbacks.forEach(div => {
            div.innerHTML = '';
        });

        // Ocultar el mensaje de victoria
        document.getElementById('win-message').style.display = 'none';

        // Ir al inicio de la página
        window.scrollTo({ top: 0, behavior: 'smooth' });
    });

});
