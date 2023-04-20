$(() => {

    id = parseInt(new URLSearchParams(window.location.search.substring(1)).get("id"));
    $('.heading').text("Delete log #" + id);
    $('.delete_button').click(() => {
        $.get("deleteLog.php", {id:id})
        .done(() => {
            window.location="readLogs.html";
        })
        .fail(() => {
            $('main').after(`
                <div class="error">
                    Server error
                </div>
            `);
        });
    });
    $('.cancel_button').click(() => {
        window.location='readLogs.html';
    });
});