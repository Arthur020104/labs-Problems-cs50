function checkRatio(event, id)
{
    let but = document.querySelector('#'+id);
    let triggerObject = event.srcElement;
    let reponse = triggerObject.innerHTML;
    let answer = document.querySelector('#response_multi');
    but.style.transition=".4s ease all"
    if(reponse == "a) eleitoral, que, ao instituir o voto direto para os cargos eletivos do Império, ao mesmo tempo em que proibiu o voto dos analfabetos, reduziu notavelmente a participação eleitoral dos setores populares.")
    {
        answer.innerHTML ="Your response is right!";
        answer.style.visibility = 'visible';
        answer.style.color= '#006400';
        but.style.backgroundColor= '#004d26';
        but.style.color= 'white';
    }
    else
    {
        answer.innerHTML ="Your response is wrong";
        answer.style.visibility = 'visible';
        answer.style.color= '#720000';
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
    if(answer.toLowerCase() == 'luis xiv')
    {
        estilo.style.backgroundColor= '#006400';
        estilo.style.color= 'white';
        response.innerHTML ="Your response is right!";
        response.style.visibility = 'visible';
        response.style.color= '#006400';
        but.style.backgroundColor= '#004d26';
    }
    else
    {
        response.innerHTML ="Your response is wrong";
        response.style.visibility = 'visible';
        response.style.color= '#720000';
        estilo.style.backgroundColor= '#720000';
        estilo.style.color= 'white';
    }
}