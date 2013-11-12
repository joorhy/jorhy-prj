.PHONY: clean All

All:
	@echo "----------Building project:[ PlayerDemo - Debug ]----------"
	@$(MAKE) -f  "PlayerDemo.mk"
clean:
	@echo "----------Cleaning project:[ PlayerDemo - Debug ]----------"
	@$(MAKE) -f  "PlayerDemo.mk" clean
