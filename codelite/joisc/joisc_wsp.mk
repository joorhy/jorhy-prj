.PHONY: clean All

All:
	@echo "----------Building project:[ ivs - Debug ]----------"
	@$(MAKE) -f  "ivs.mk"
clean:
	@echo "----------Cleaning project:[ ivs - Debug ]----------"
	@$(MAKE) -f  "ivs.mk" clean
