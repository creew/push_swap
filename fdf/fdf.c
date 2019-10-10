
#include "fdf.h"
#include "mlx.h"

int		main(int ac, char *av[])
{
	void *mlx_data;
	void *mlx_window;

	mlx_data = mlx_init();
	if (mlx_data)
	{
		mlx_window = mlx_new_window(mlx_data, 1000,1000, "Превед!");
		mlx_loop(mlx_data);
	}
	return (0);
}