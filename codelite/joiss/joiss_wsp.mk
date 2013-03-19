.PHONY: clean All

All:
	@echo ----------Building project:[ utils - Debug ]----------
	@"$(MAKE)" -f "utils.mk"
clean:
	@echo ----------Cleaning project:[ utils - Debug ]----------
	@"$(MAKE)" -f "utils.mk" clean
