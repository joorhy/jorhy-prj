.PHONY: clean All

All:
	@echo ----------Building project:[ joiss - Debug ]----------
	@"$(MAKE)" -f "joiss.mk"
clean:
	@echo ----------Cleaning project:[ joiss - Debug ]----------
	@"$(MAKE)" -f "joiss.mk" clean
