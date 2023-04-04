window.addEventListener("DOMContentLoaded", () => {
    ROWS = 3;
    COLUMNS = 3;

    const imageContainer = document.querySelector(".image-container");
    const wellDoneText = document.querySelector(".well-done-text");
    wellDoneText.style.display = 'none';

    cells = []
    for (let i = 0; i < ROWS; i++) {
        for (let j = 0; j < COLUMNS; j++) {
            let cell = document.createElement('div');
            cell.setAttribute('cell-id', i * COLUMNS + j);
            cell.setAttribute('class', 'image-container__cell');
            cell.style.backgroundImage = 'url("knight.jpg")';
            cell.style.backgroundPosition = `-${j * 800 / 3}px -${i * 800 / 3}px`;
            cells.push(cell)
        }
    }

    cells = cells
        .map(value => ({ value, sort: Math.random() }))
        .sort((a, b) => a.sort - b.sort)
        .map(({ value }) => value);

    cells.forEach(cell => imageContainer.appendChild(cell));

    function checkSolved() {
        let solved = true;
        for (let i = 0; i < cells.length; i++) {
            if (cells[i].getAttribute('cell-id') != i) {
                solved = false;
                break;
            }
        }
        if (solved) {
            wellDoneText.style.display = "block";
        } else {
            wellDoneText.style.display = "none";
        }
    }


    let currentCell = -1;
    function onClickEvent(event) {
        let cellId = event.target.getAttribute('cell-id');
        if (currentCell != -1) {
            let cellIdIndex = -1;
            let currentCellIndex = -1;

            for (let i = 0; i < cells.length; i++) {
                if (cells[i].getAttribute('cell-id') == cellId) {
                    cellIdIndex = i;
                }
                if (cells[i].getAttribute('cell-id') == currentCell) {
                    currentCellIndex = i;
                }
            }

            tempCell = cells[cellIdIndex];
            cells[cellIdIndex] = cells[currentCellIndex];
            cells[currentCellIndex] = tempCell;

            while (imageContainer.firstChild) {
                imageContainer.removeChild(imageContainer.lastChild);
            }

            cells.forEach(cell => imageContainer.appendChild(cell));
            currentCell = -1;
        } else {
            currentCell = cellId;
        }
        checkSolved();
    };

    cells.forEach(cell => {
        cell.addEventListener('click', onClickEvent);
    })

})