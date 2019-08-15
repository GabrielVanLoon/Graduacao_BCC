
/**
 * FIXED SIDEBAR
 * Verifica se a tela está próxima de cobrir o sidebar e torna ele fixo
 */
    function ajustarSidebar(){
        var distSidebar = $('#sidebar').offset().top;
        var posWindow   = $(window).scrollTop();
        var maxWidth    =  $('#sidebar').width()

        if( distSidebar - posWindow <= 40){
            $('#sidebar').addClass("fixed");
            $('#sidebar ul').css("max-width", maxWidth);
        } else {
            $('#sidebar').removeClass("fixed");
        }
           
    }
    $(window).on('scroll', ajustarSidebar);
    ajustarSidebar();

/**
 * SCROLL SPY
 * Verifica qual conteúdo está sendo mostrado e marca como ativo no menu de sidebar
 */
    function scrollSpy(){
        // Verificando qual é a sessão em foco atual
        var sessaoAtual = null;
        var offset      = 40;
        $(".spy-this section").each(function(){

            var distTop = $(this).offset().top;
            var posWindow   = $(window).scrollTop();

            if( (posWindow + 80) < (distTop + $(this).height())  && sessaoAtual == null){
                sessaoAtual = $(this).attr('id');
            }
            // alert($( this ).attr("id"));
        });

        // alert(sessaoAtual);

        $('#sidebar li a').removeClass('active');
        $('#sidebar li a').filter('[href="#'+sessaoAtual+'"]').addClass('active');
    }
    $(window).on('scroll',  scrollSpy);
    scrollSpy();

/**
 * SMOOTH SCROLLING
 * Efeito de rolagem suave para quando algum item da sidebar é selecionado
 */
    $("#sidebar li a").on('click', function(event) {
        event.preventDefault();
        var sessao = this.hash;
        $('html, body').animate({
            scrollTop: $(sessao).offset().top
        }, 800, function(){
        window.location.hash = sessao;
      });
    });