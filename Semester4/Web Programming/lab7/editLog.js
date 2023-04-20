$(() => {

    // Validates that the input string is a valid date formatted as "mm/dd/yyyy"
    function isValidDate(dateString) {
        // First check for the pattern
        if(!/^\d{4}-\d{2}-\d{2}$/.test(dateString))
            return false;

        // Parse the date parts to integers
        var parts = dateString.split("-");
        var day = parseInt(parts[2], 10);
        var month = parseInt(parts[1], 10);
        var year = parseInt(parts[0], 10);

        // Check the ranges of month and year
        if(year < 1000 || year > 3000 || month == 0 || month > 12)
            return false;

        var monthLength = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];

        // Adjust for leap years
        if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
            monthLength[1] = 29;

        // Check the range of the day
        return day > 0 && day <= monthLength[month - 1];
    };

    id = parseInt(new URLSearchParams(window.location.search.substring(1)).get("id"));
    $('.heading').text("Edit log #" + id);
    $.getJSON("readLog.php", {id:id}, json => {
        $('.input_form__severity').val(json[0]["severity"]);
        $('.input_form__date').val(json[0]["logDate"]);
        $('.input_form__user').val(json[0]["user"]);
        $('.input_form__text').val(json[0]["data"]);
    });

    $(".input_form__buttons__cancel").click((e) => {
        e.preventDefault();
        window.location='readLogs.html';
    });

    $(".input_form__buttons__add").click((e) => {
        e.preventDefault();
        $('.input_form__error').remove();

        let severity = $('.input_form__severity').val().trim();
        let date = $('.input_form__date').val().trim();
        let user = $('.input_form__user').val().trim();
        let text = $('.input_form__text').val().trim();
        let valid = true;

        if(severity === "") {
            $('.input_form__severity').after(`
                <div class="input_form__error">
                    Severity cannot be empty.
                </div>
            `);
            valid = false;
        }

        if(user === "") {
            $('.input_form__user').after(`
                <div class="input_form__error">
                    User cannot be empty.
                </div>
            `);
            valid = false;
        }

        if(!isValidDate(date)) {
            $('.input_form__date').after(`
                <div class="input_form__error">
                    Date should be of the following format: YYYY-MM-DD.
                </div>
            `);
            valid = false;
        }

        if(text === "") {
            $('.input_form__text').after(`
                <div class="input_form__error">
                    Text cannot be empty.
                </div>
            `);
            valid = false;
        }

        if(valid) {
            $.post("editLog.php", {id:id, severity:severity, date:date, user:user, text:text})
                .done(() => {
                    window.location="readLogs.html";
                })
                .fail(() => {
                    $('.input_form').after(`
                        <div class="input_form__error">
                            Server error
                        </div>
                    `);
                });
        }
    });
});