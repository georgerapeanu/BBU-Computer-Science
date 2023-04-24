$(() => {
    id = parseInt(new URLSearchParams(window.location.search.substring(1)).get("id"));
    $('.heading').text("Read log #" + id);
    $.getJSON("readLog.php", { id: id }, json => {
        $('.input_form__severity').val(json[0]["severity"]);
        $('.input_form__date').val(json[0]["logDate"]);
        $('.input_form__user').val(json[0]["user"]);
        $('.input_form__text').val(json[0]["data"]);
    });
});