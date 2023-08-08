program:
	g++ test.cpp AbstractProduct.h AbstractProduct.cpp Fisico.h Fisico.cpp IProductVisitor.h Renderer.h Renderer.cpp IConstProductVisitor.h JsonVisitor.h JsonVisitor.cpp Virtuale.h Virtuale.cpp Noleggio.h Noleggio.cpp Container.h

clean:
	rm *.out
	rm *.h.gch
