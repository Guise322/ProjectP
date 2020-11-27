window.fitContent = () => {
    var TextArea = document.getElementById('textarea-to-fit-content');
    TextArea.style.height='auto';
    TextArea.style.height=(TextArea.scrollHeight)+'px';
}