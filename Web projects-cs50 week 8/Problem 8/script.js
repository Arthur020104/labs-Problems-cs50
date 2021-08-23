
function checktf(event,id)
{
    let but = document.querySelector('#'+id);
    let triggerObject = event.srcElement;//quando acontece tal evento (onclick) peg o elemento da fonte
    let reponse = triggerObject.innerHTML;
    let answer = document.querySelector("#response_multi");
    but.style.transition=".4s ease all";
    answer.style.transition=".4s ease all";
    if(id == "buttrue")
    {
        answer.innerHTML ="Your response is right!";
        answer.className="alert alert-success";
        answer.style.visibility = 'visible';
        but.style.backgroundColor= '#004d26';
        but.style.color= 'white';
    }
    else
    {
        answer.innerHTML ="Your response is wrong";
        answer.className="alert alert-danger";
        answer.style.visibility = 'visible';
        but.style.backgroundColor= '#720000';
        but.style.color= 'white';
    }
}
function submit()
{
    let response = document.querySelector('#response_free');
    let answer = document.querySelector('#answer').value;
    let estilo = document.querySelector('#answer');
    estilo.style.transition=".5s ease all"
    response.style.transition=".4s ease all";
    if(answer.toLowerCase() == 'ufu')
    {
        estilo.style.backgroundColor= 'rgb(10, 85, 3)';
        estilo.style.color= 'rgb(0, 255, 42)';
        response.innerHTML ="Your response is right!";
        response.className="alert alert-success";
        response.style.visibility = 'visible';
    }
    else
    {
        response.innerHTML = "Your response is wrong";
        response.className="alert alert-danger";
        response.style.visibility = 'visible';
        estilo.style.backgroundColor= '#720000';
        estilo.style.color= 'white';
    }
}