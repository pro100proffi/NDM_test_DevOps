# Trust only known nginx containers by exact IP address.
# Any request from another address is considered an external user request,
# therefore user-supplied X-Forwarded-For must be ignored.
geo $from_trusted_nginx {
    default     0;
    172.28.0.11 1; # nginx1
    172.28.0.12 1; # nginx2
    172.28.0.13 1; # nginx3
}

# If request came from trusted nginx, append current nginx IP to existing chain.
# If request came from user/untrusted peer, start a clean chain from $remote_addr.
map $from_trusted_nginx $clean_x_forwarded_for {
    0 $remote_addr;
    1 $proxy_add_x_forwarded_for;
}
