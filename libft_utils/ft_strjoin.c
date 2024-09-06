char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;

	if (!s2)
		return (NULL);
	if (_strlen(s2) == 1 && s2[0] == '\n')
	{
		free(s2);
		printf("Error: Invalid map\n");
		exit(1);
	}
	dlen = _strlen(s1);
	slen = _strlen(s2);
	str = malloc((dlen + slen + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	_memcpy(str, s1, dlen);
	_memcpy(str + dlen, s2, slen);
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}