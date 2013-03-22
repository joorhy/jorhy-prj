.PHONY: clean All

All:
	@echo ----------Building project:[ joies - Debug ]----------
	@"$(MAKE)" -f "joies.mk"
clean:
	@echo ----------Cleaning project:[ joies - Debug ]----------
	@"$(MAKE)" -f "joies.mk" clean
