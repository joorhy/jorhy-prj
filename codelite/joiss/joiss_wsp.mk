.PHONY: clean All

All:
	@echo ----------Building project:[ AironixHost - Debug ]----------
	@"$(MAKE)" -f "AironixHost.mk"
clean:
	@echo ----------Cleaning project:[ AironixHost - Debug ]----------
	@"$(MAKE)" -f "AironixHost.mk" clean
