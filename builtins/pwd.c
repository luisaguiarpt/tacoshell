int ft_pwd(t_core *core)
{
  int i;
  i = -1;

  while (core->cwd[i++])
    write(1, &cwd[i], 1);
  write(1, "\n", 1);
  return (EXIT_SUCCESS);
}
