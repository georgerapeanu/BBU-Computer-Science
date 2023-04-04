$(document).ready(() => {

    let focusedImageId = -1;

    const unfocusImage = (event) => {
        $('.focused-image').remove();
        focusedImageId = -1;
        speed = 1;
    }

    const focusImage = (event) => {
        if(focusedImageId == -1){
            focusedImageId = event.target.getAttribute('image-id');
            speed = 0;
            let img = $('<img>').attr('class', 'focused-image').attr('src', `https://via.placeholder.com/200x200?text=${focusedImageId}`);
            img.on('click', unfocusImage);
            $('main').append(img);
        }
    }

    const IMAGE_COUNT = 9;

    let image_container = $('.image-container');
    for(let i = 0;i < IMAGE_COUNT;i++){
        let image = $('<img>');
        image.attr('class', 'image-container__slider-image');
        image.attr('src', `https://via.placeholder.com/200x200?text=${i}`);
        image.on('click', focusImage);
        image.attr('image-id', i);
        image_container.append(image);
    }

    const DURATION = 1000;
    const DISTANCE = 200;
    let speed = 1;

    function slideRight() {
        const images = image_container.find('.image-container__slider-image');
        image_container.animate({"padding-left": '+=' + DISTANCE * speed}, DURATION, 'linear', () => {
            if(images.last().position().left > image_container.width()) {
                let last_image = images.last();
                last_image.remove();
                image_container.prepend(last_image);
                image_container.css('padding-left', 0);
            }
        });
    }

    setInterval(slideRight, DURATION);
    
})